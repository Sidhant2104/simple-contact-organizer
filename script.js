// Contact storage (using localStorage for persistence)
let contacts = JSON.parse(localStorage.getItem('contacts')) || [];

// DOM elements
const contactForm = document.getElementById('contactForm');
const contactsList = document.getElementById('contactsList');
const searchInput = document.getElementById('searchInput');
const messageDiv = document.getElementById('message');

// Initialize app
document.addEventListener('DOMContentLoaded', function() {
    displayContacts();
    
    // Form submission
    contactForm.addEventListener('submit', function(e) {
        e.preventDefault();
        addContact();
    });
    
    // Real-time search
    searchInput.addEventListener('input', function() {
        if (this.value.trim() === '') {
            displayContacts();
        } else {
            searchContacts();
        }
    });
});

// Validation functions
function isValidPhone(phone) {
    const phoneRegex = /^[\d\s\-\(\)]{10,}$/;
    return phoneRegex.test(phone);
}

function isValidEmail(email) {
    if (!email) return true; // Email is optional
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

// Add new contact
function addContact() {
    const name = document.getElementById('name').value.trim();
    const phone = document.getElementById('phone').value.trim();
    const email = document.getElementById('email').value.trim();
    
    // Validation
    if (!name || !phone) {
        showMessage('Please fill in name and phone number', 'error');
        return;
    }
    
    if (!isValidPhone(phone)) {
        showMessage('Please enter a valid phone number (at least 10 digits)', 'error');
        return;
    }
    
    if (email && !isValidEmail(email)) {
        showMessage('Please enter a valid email address', 'error');
        return;
    }
    
    // Check for duplicates
    if (contacts.find(contact => contact.name.toLowerCase() === name.toLowerCase())) {
        showMessage('Contact with this name already exists', 'error');
        return;
    }
    
    // Add contact
    const newContact = {
        id: Date.now(),
        name: name,
        phone: phone,
        email: email || ''
    };
    
    contacts.push(newContact);
    saveContacts();
    displayContacts();
    contactForm.reset();
    showMessage('Contact added successfully!', 'success');
}

// Delete contact
function deleteContact(id) {
    if (confirm('Are you sure you want to delete this contact?')) {
        contacts = contacts.filter(contact => contact.id !== id);
        saveContacts();
        displayContacts();
        showMessage('Contact deleted successfully!', 'success');
    }
}

// Search contacts
function searchContacts() {
    const query = searchInput.value.toLowerCase().trim();
    if (!query) {
        displayContacts();
        return;
    }
    
    const filtered = contacts.filter(contact => 
        contact.name.toLowerCase().includes(query) ||
        contact.phone.includes(query) ||
        contact.email.toLowerCase().includes(query)
    );
    
    displayContacts(filtered);
}

// Show all contacts
function showAllContacts() {
    searchInput.value = '';
    displayContacts();
}

// Display contacts
function displayContacts(contactsToShow = contacts) {
    if (contactsToShow.length === 0) {
        contactsList.innerHTML = '<div class="empty-state">No contacts found</div>';
        return;
    }
    
    contactsList.innerHTML = contactsToShow.map(contact => `
        <div class="contact-card">
            <div class="contact-name">${escapeHtml(contact.name)}</div>
            <div class="contact-info">📞 ${escapeHtml(contact.phone)}</div>
            ${contact.email ? `<div class="contact-info">✉️ ${escapeHtml(contact.email)}</div>` : ''}
            <div class="contact-actions">
                <button class="delete-btn" onclick="deleteContact(${contact.id})">Delete</button>
            </div>
        </div>
    `).join('');
}

// Save contacts to localStorage
function saveContacts() {
    localStorage.setItem('contacts', JSON.stringify(contacts));
}

// Show message
function showMessage(text, type) {
    messageDiv.textContent = text;
    messageDiv.className = `message ${type}`;
    messageDiv.style.display = 'block';
    
    setTimeout(() => {
        messageDiv.style.display = 'none';
    }, 3000);
}

// Escape HTML to prevent XSS
function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}

// Export contacts as JSON
function exportContacts() {
    const dataStr = JSON.stringify(contacts, null, 2);
    const dataBlob = new Blob([dataStr], {type: 'application/json'});
    const url = URL.createObjectURL(dataBlob);
    const link = document.createElement('a');
    link.href = url;
    link.download = 'contacts.json';
    link.click();
    URL.revokeObjectURL(url);
}

// Import contacts from JSON
function importContacts(event) {
    const file = event.target.files[0];
    if (!file) return;
    
    const reader = new FileReader();
    reader.onload = function(e) {
        try {
            const importedContacts = JSON.parse(e.target.result);
            if (Array.isArray(importedContacts)) {
                contacts = importedContacts;
                saveContacts();
                displayContacts();
                showMessage('Contacts imported successfully!', 'success');
            } else {
                showMessage('Invalid file format', 'error');
            }
        } catch (error) {
            showMessage('Error reading file', 'error');
        }
    };
    reader.readAsText(file);
}